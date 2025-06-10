#pragma once

#include "speed_density_base.h"
#include "maf_airmass.h"

class SpeedDensityAirmass : public SpeedDensityBase {
public:
	explicit SpeedDensityAirmass(const ValueProvider3D& veTable, const ValueProvider3D& mapEstimationTable)
		: SpeedDensityBase(veTable)
		, m_mapEstimationTable(&mapEstimationTable)
	{ m_mode = LM_SPEED_DENSITY; }

	AirmassResult getAirmass(float rpm, bool postState) override;
	AirmassResult getAirmass(float rpm, float map, bool postState);
	float getAirflow(float rpm, float map, bool postState);

	float getMap(float rpm, bool postState) const;

private:
	const ValueProvider3D* const m_mapEstimationTable;
};


class MAFMAPAirmass : public AirmassModelBase {
public:
	explicit MAFMAPAirmass(SpeedDensityAirmass& sdAirmass, MafAirmass& mafAirmass, const ValueProvider3D& mafmapblend)
		: m_sdAirmass(sdAirmass)
		, m_mafAirmass(mafAirmass)
		, m_mafmapblend(&mafmapblend)
	{}

	AirmassResult getAirmass(float rpm, bool postState) override ;
	// AirmassResult getAirmass(float rpm, float map, bool postState);
	float getAirflow(float rpm, float map, bool postState);

	float getMap(float rpm, bool postState) const;

private:
	SpeedDensityAirmass& m_sdAirmass;
	MafAirmass& m_mafAirmass;
	const ValueProvider3D* const m_mafmapblend;
};
