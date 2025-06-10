package com.opensr5.ini;

import java.util.ArrayList;
import java.util.List;

/**
 * Andrey Belomutskiy, (c) 2013-2020
 * 3/1/2017
 */
public class IniFileMetaInfoImpl implements IniFileMetaInfo {
    public static final int DEFAULT_BLOCKING_FACTOR = 16000;
    private final int nPages;
    private final String signature;
    private final List<String> pageReadCommands;

    private int totalSize;
    private final List<Integer> pageSizes = new ArrayList<>();
    private final int ochBlockSize;

    /**
     * read maximum chunk size
     */
    private final int blockingFactor; // todo: this is probably an optional property, come up with some default

    public IniFileMetaInfoImpl(RawIniFile file) {

        try {
            nPages = file.getSimpleIntegerProperty("nPages", 1);
            ochBlockSize = file.getSimpleIntegerProperty("ochBlockSize");

            blockingFactor = file.getSimpleIntegerProperty("blockingFactor", DEFAULT_BLOCKING_FACTOR);

            signature = file.getValues("signature").get(0);

            List<String> individualPageSizes = file.getValues("pageSize");

            if (individualPageSizes.size() != nPages)
                throw new IllegalStateException("Unexpected individual sizes: " + individualPageSizes);

            for (String value : individualPageSizes) {
                int size = Integer.parseInt(value);
                pageSizes.add(size);
                totalSize += size;
            }

            pageReadCommands = file.getValues("pageReadCommand");
        } catch (MandatoryLineMissing e) {
            throw new RuntimeException("While reading " + file.msg, e);
        }
    }

    public int getnPages() {
        return nPages;
    }

    public int getOchBlockSize() {
        return ochBlockSize;
    }

    public int getBlockingFactor() {
        return blockingFactor;
    }

    // also known as 'pageSize'
    public int getTotalSize() {
        return totalSize;
    }

    @Override
    public String getSignature() {
        return signature;
    }

    @Override
    public String getPageReadCommand(int pageIndex) {
        return pageReadCommands.get(pageIndex);
    }

    @Override
    public int getPageSize(int pageIndex) {
        return pageSizes.get(pageIndex);
    }
}
