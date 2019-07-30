@echo OFF
devenv /clean debug RulesBasedAlertingSystem\RulesBasedAlertingSystem.sln
devenv /build debug RulesBasedAlertingSystem\RulesBasedAlertingSystem.sln
devenv /clean debug DataFeeder\DataFeeder.sln
devenv /build debug DataFeeder\DataFeeder.sln

   set /p answer=Open in Registration Mode (Y/N)?
   if /i "%answer:~,1%" EQU "Y" RulesBasedAlertingSystem\x64\Debug\RulesBasedAlertingSystem.Host.exe
   if /i "%answer:~,1%" EQU "N" DataFeeder\Debug\DataFeeder.exe | RulesBasedAlertingSystem\x64\Debug\RulesBasedAlertingSystem.Host.exe



pause