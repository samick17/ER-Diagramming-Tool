SET PATH=c:\Program Files (x86)\Microsoft Visual Studio 10.0\Team Tools\Performance Tools\
vsinstr @CommandOption.txt
vsperfcmd -start:coverage -output:CodeCoverageDemo.coverage
102598045_TEST.exe
vsperfcmd -shutdown
echo Complete!
pause