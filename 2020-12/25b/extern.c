extern void (*value)();

void loadValue() {
	value = 12;
}

value = loadValue;