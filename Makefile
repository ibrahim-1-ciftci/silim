.PHONY: all c2 gui dropper payload_win payload_lin payload_mac payload_android driver clean

all: c2 gui dropper payload_win payload_lin payload_mac payload_android driver

c2:
	cd c2_server && go build -o c2_server main.go

gui:
	cd gui_panel && pyinstaller --onefile main.py --name gui_panel

dropper:
	cd dropper && chmod +x build_all.sh && ./build_all.sh

payload_win:
	cd payload_windows && cmd /c build.bat

payload_lin:
	cd payload_linux && chmod +x build.sh && ./build.sh

payload_mac:
	cd payload_macos && chmod +x build.sh && ./build.sh

payload_android:
	cd payload_android && ndk-build

driver:
	cd kernel_driver && cmd /c build.bat

clean:
	rm -rf c2_server/c2_server gui_panel/dist dropper/dropper* payload_*/*.exe payload_*/*.so payload_*/*.dylib payload_android/libs