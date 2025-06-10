#include "pch.h"

#include "closed_loop_fuel.h"
#include "closed_loop_fuel_cell.h"
#include "tunerstudio.h"

#if EFI_ENGINE_CONTROL

struct FuelingBank {
	ClosedLoopFuelCellImpl cell;
};

static FuelingBank banks[STFT_BANK_COUNT];

namespace {
	SensorType getSensorForBankIndex(size_t index) {
		switch (index) {
			case 0: return SensorType::Lambda1;
			case 1: return SensorType::Lambda2;
			default: return SensorType::Invalid;
		}
	}
}


namespace {
	bool shouldCorrect() {
		const auto& cfg = engineConfiguration->stft;

		// User disable bit
		if (!engineConfiguration->fuelClosedLoopCorrectionEnabled) {
			return false;
		}

		// Don't correct if not running
		if (!engine->rpmCalculator.isRunning()) {
			return false;
		}

		// Startup delay - allow O2 sensor to warm up, etc
		if (cfg.startupDelay > engine->fuelComputer.running.timeSinceCrankingInSecs) {
			return false;
		}

		// Check that the engine is hot enough (and clt not failed)
		auto clt = Sensor::get(SensorType::Clt);
		if (!clt.Valid || clt.Value < cfg.minClt) {
			return false;
		}

		// If all was well, then we're enabled!
		return true;
	}
}

bool shouldUpdateCorrection(SensorType sensor) {
	const auto& cfg = engineConfiguration->stft;

	// Pause (but don't reset) correction if the AFR is off scale.
	// It's probably a transient and poorly tuned transient correction
	auto afr = Sensor::getOrZero(sensor) * STOICH_RATIO;
	if (!afr || afr < cfg.minAfr || afr > cfg.maxAfr) {
		return false;
	}

	// Pause correction if DFCO was active recently
	auto timeSinceDfco = engine->module<DfcoController>()->getTimeSinceCut();
	if (timeSinceDfco < engineConfiguration->noFuelTrimAfterDfcoTime) {
		return false;
	}

	// Pause if some other cut was active recently
	auto timeSinceFuelCut = engine->module<LimpManager>()->getTimeSinceAnyCut();
	// TODO: should duration this be configurable?
	if (timeSinceFuelCut < 2) {
		return false;
	}

	if (engine->module<TpsAccelEnrichment>()->extraFuel > 0.0f) { // if there's any extra fuel from TPS AE still active.
		return false;
	}

	// resume EGO once we're off the tpsAeCycle map
	if (engine->module<TpsAccelEnrichment>()->tpsAeCycleCnt < config->tpsAeCycleCycleBins[TPS_AE_MAP-1] ) {
		return false;
	}

	return true;
}

ClosedLoopFuelResult fuelClosedLoopCorrection() {
	engine->outputChannels.stftNotCorrecting = 0;

	if (!shouldCorrect()) {
		engine->outputChannels.stftNotCorrecting = 1;
		return {};
	}

	ClosedLoopFuelResult result;

	for (int i = 0; i < STFT_BANK_COUNT; i++) {
		// auto& cell = banks[i].cells[binIdx];
		auto& cell = banks[i].cell;

		SensorType sensor = getSensorForBankIndex(i);
		if (!Sensor::hasSensor(sensor)) {
			result.banks[i] = 1.0f;
			return result;
		}

		// todo: push configuration at startup
		// cell.configure(&engineConfiguration->stft.cellCfgs[binIdx], sensor);
		cell.configure(&engineConfiguration->stft.cell, sensor);

		if (shouldUpdateCorrection(sensor)) {
			engine->outputChannels.stftNotUpdating = 0;
			cell.update(engineConfiguration->stft.deadband * 0.01f, engineConfiguration->stftIgnoreErrorMagnitude);
		} else {
			engine->outputChannels.stftNotUpdating = 1;
		}

		// if tpsAeResetsEgo
		if (engineConfiguration->tpsAeResetsEgo && 	(engine->module<TpsAccelEnrichment>()->extraFuel > 0.0f) ) {
			banks[i].cell.setAdjustment(0.0f);
			engine->outputChannels.stftNotCorrecting = 1;
		}

        result.banks[i] = cell.getAdjustment();
	}

	return result;
}

#endif // EFI_ENGINE_CONTROL