#-------------------------------------------------------------------------------
#   oryol core module
#-------------------------------------------------------------------------------
fips_begin_module(Core)
    fips_vs_warning_level(3)
    if (FIPS_MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    endif()
    fips_files(
        App.cc App.h
        AppState.cc AppState.h
        Args.cc Args.h
        Assertion.h
        Class.h
        Config.h
        Core.cc Core.h
        Creator.h
        Log.cc Log.h
        Logger.cc Logger.h
        Macros.h
        Ptr.h
        RefCounted.cc RefCounted.h
        RunLoop.cc RunLoop.h
        Types.h
        precompiled.h
    )
    fips_dir(Containers)
    fips_files(
        Array.h
        ArrayMap.h
        HashSet.h
        KeyValuePair.h
        Map.h
        Queue.h
        Set.h
        StaticArray.h
        elementBuffer.h
    )
    fips_dir(Memory)
    fips_files(Memory.cc Memory.h poolAllocator.h)
    fips_dir(String)
    fips_files(
        String.cc String.h
        StringAtom.cc StringAtom.h
        StringBuilder.cc StringBuilder.h
        StringConverter.cc StringConverter.h
        WideString.cc WideString.h
        stringAtomBuffer.cc stringAtomBuffer.h
        stringAtomTable.cc stringAtomTable.h
    )
    fips_dir(Threading)
    fips_files(
        RWLock.h
        ThreadLocalData.cc ThreadLocalData.h
        ThreadLocalPtr.h
    )
    if (FIPS_POSIX)
        fips_dir(posix)
        fips_files(precompiled.h)
    endif()
    if (FIPS_WINDOWS)
        fips_dir(windows)
        fips_files(precompiled.h)
    endif()
    if (FIPS_ANDROID)
        fips_dir(android)
        fips_files(androidBridge.cc androidBridge.h)
        fips_deps(android_native)
    endif()
    if (FIPS_IOS)
        fips_dir(ios)
        fips_files(
            iosAppDelegate.mm iosAppDelegate.h
            iosBridge.mm iosBridge.h
        )
    endif()
    if (FIPS_PNACL)
        fips_dir(pnacl)
        fips_files(
            pnaclInstance.cc pnaclInstance.h
            pnaclModule.cc pnaclModule.h
        )
    endif()
    fips_deps(ConvertUTF)
    fips_dir(.)
    fips_files(Trace.h Trace.cc)
    if (FIPS_PROFILING AND (FIPS_LINUX OR FIPS_MACOS OR FIPS_WINDOWS))
        fips_deps(Remotery)
    endif()
    if (FIPS_USE_VLD)
        fips_libs(vld)
    endif()
fips_end_module()
if (FIPS_USE_VLD)
    add_dependencies(Core vld_copy_dlls)
endif()

fips_begin_unittest(Core)
    fips_vs_warning_level(3)
    fips_dir(UnitTests)
    fips_files(
        ArgsTest.cc
        ArrayTest.cc
        StaticArrayTest.cc
        ArrayMapTest.cc
        CreationTest.cc
        CreatorTest.cc
        HashSetTest.cc
        MapTest.cc
        MemoryTest.cc
        PoolAllocatorTest.cc
        QueueTest.cc
        RttiTest.cc
        RunLoopTest.cc
        SetTest.cc
        StringAtomTest.cc
        StringBuilderTest.cc
        StringConverterTest.cc
        StringTest.cc
        WideStringTest.cc
        elementBufferTest.cc
    )
    fips_deps(Core)
fips_end_unittest()

