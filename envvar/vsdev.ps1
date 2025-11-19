function vsdev {
    $vsPath = "C:\Program Files\Microsoft Visual Studio\18\Enterprise\VC\Auxiliary\Build\vcvars64.bat"  
    cmd.exe /c "call `"$vsPath`" && set" | ForEach-Object {
        if ($_ -match "^(.*?)=(.*)$") {
            Set-Content "env:$($matches[1])" $matches[2]
        }
    }
    Write-Host "Visual Studio Environment Loaded!" -ForegroundColor Green
}