build:
	arduino-cli compile --fqbn arduino:avr:uno .

deploy: build
	arduino-cli upload -t -v -p /dev/ttyACM0 --fqbn arduino:avr:uno .
