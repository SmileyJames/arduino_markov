build:
	arduino-cli compile --fqbn arduino:avr:uno .

deploy:
	arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno .
