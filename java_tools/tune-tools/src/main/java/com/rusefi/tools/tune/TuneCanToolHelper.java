package com.rusefi.tools.tune;

import com.opensr5.ini.IniFileModelImpl;
import com.rusefi.RootHolder;
import org.jetbrains.annotations.NotNull;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

public class TuneCanToolHelper {
    public static final Set<String> IGNORE_LIST = new TreeSet<>(String.CASE_INSENSITIVE_ORDER);
    protected static void initialize(String iniFileName) {
        TuneCanTool.ini = IniFileModelImpl.readIniFile(iniFileName);
    }

    static void readIgnoreList(String ignoreListFileName) throws IOException {
        List<@NotNull String> lines = Files.readAllLines(Paths.get(ignoreListFileName));
        for(String line : lines)
            IGNORE_LIST.add(line.trim());
    }
}
