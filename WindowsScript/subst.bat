@echo OFF
SET "_FullString=%~3"
SET "_Search=%~1"
SET "_Replace=%~2"
CALL SET "_result=%%_FullString:%_Search%=%_Replace%%%"
@echo %_result%