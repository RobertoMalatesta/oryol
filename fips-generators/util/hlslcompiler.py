'''
Python wrapper for HLSL compiler (fxc.exe)

NOTE: this module contains Windows specific code and should
only be imported when running on Windows.
'''
import subprocess
import tempfile
import platform
import os
import genutil as util
import _winreg

#-------------------------------------------------------------------------------
def findFxc() :
    '''
    fcx.exe is located in the 'Windows Kits' SDKs, we first check the
    registry for the installation paths, and then see if we can 
    find the fxc.exe file there under 'bin/x86'

    Returns an unicode path string of fxc.exe if found, or None if
    not found.
    '''
    fcxPath = None;

    # first get the preferred kit name (either 8.1 or 10, are there others?)
    try :
        with _winreg.OpenKey(_winreg.HKEY_LOCAL_MACHINE, 'Software\\Microsoft\\Windows Kits\\Installed Roots') as key :
            for kit in ['KitsRoot10', 'KitsRoot81'] :
                try :
                    fxcPath, _ = _winreg.QueryValueEx(key, kit)
                    break
                except :
                    fxcPath = None

        fxcPath += u'bin\\x86\\fxc.exe'
        if os.path.isfile(fxcPath) :
            return fxcPath
        else :
            return None

    except WindowsError :
        return None

#-------------------------------------------------------------------------------
def writeFile(f, lines) :
    '''
    Write an array of lines to a file.
    '''
    for line in lines :
        f.write(line.content + '\n')

#-------------------------------------------------------------------------------
def callFxc(cmd) :
    ''' 
    call the fxc compiler and return its output
    '''
    child = subprocess.Popen(cmd, stderr=subprocess.PIPE)
    out = ''
    while True :
        out += child.stderr.read()
        if child.poll() != None :
            break
    return out

#-------------------------------------------------------------------------------
def parseOutput(output, lines) :
    '''
    Parse error output lines from the GLSL reference compiler,
    map them to the original source code location and output
    an error message compatible with Xcode or VStudio
    '''
    hasError = False
    hasWarning = False
    outLines = output.splitlines()

    for outLine in outLines :

        # extract generated shader source column, line and message
        # format is 'filename(line,startcol-endcol): msg
        lineStartIndex = outLine.find('(', 0) + 1
        if lineStartIndex == 0 :
            continue
        lineEndIndex = outLine.find(',', lineStartIndex)
        if lineEndIndex == -1 :
            continue
        colStartIndex = lineEndIndex + 1
        colEndIndex = outLine.find('-', colStartIndex)
        if colEndIndex == -1 :
            continue
        msgStartIndex = outLine.find(':', colStartIndex+1)
        if msgStartIndex == -1 :
            continue

        colNr = int(outLine[colStartIndex:colEndIndex])
        lineNr = int(outLine[lineStartIndex:lineEndIndex])
        msg = outLine[msgStartIndex:]

        # map to original location
        lineIndex = lineNr - 1
        if lineIndex >= len(lines) :
            lineIndex = len(lines) - 1
        srcPath = lines[lineIndex].path
        srcLineNr = lines[lineIndex].lineNumber
        
        # and output...
        util.setErrorLocation(srcPath, srcLineNr)
        if 'error' in outLine :
            hasError = True
            util.fmtError(msg, False)
        elif 'warning' in outLine :
            hasWarning = True
            util.fmtWarning(msg)

    if hasError or hasWarning:
        for line in lines :
            print "{}, {}: {}".format(line.path, line.lineNumber, line.content)
    if hasError :
        util.fmtError("Aborting.")

#-------------------------------------------------------------------------------
def validate(lines, type, slVersion) :
    '''
    Validate a vertex-/fragment-shader pair.
    '''
    fxcPath = findFxc()
    if not fxcPath :
        fmt.fmtError("fxc.exe not found!\n")

    ext = {
        'vs': '.vsh',
        'fs': '.psh'
    }
    profile = {
        'vs': 'vs_5_0',
        'fs': 'ps_5_0'
    }

    f = tempfile.NamedTemporaryFile(suffix=ext[type], delete=False)
    writeFile(f, lines)
    f.close()

    cmd = [fxcPath, '/T', profile[type], '/O3', f.name]
    output = callFxc(cmd)
    os.unlink(f.name)
    parseOutput(output, lines)
