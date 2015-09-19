char* humanToLogicalLookup(char* recname)
{
	if (strcmp(recname, "adder") == 0) {
		return "100.001";
	}

	else if (strcmp(recname, "bear") == 0) {
		return "100.010";
	}

	else if (strcmp(recname, "cat") == 0) {
		return "101.001";
	}

	else if (strcmp(recname, "deer") == 0) {
		return "101.010";
	}

	else if (strcmp(recname, "eagle") == 0) {
		return "110.001";
	}

	else if (strcmp(recname, "fox") == 0) {
		return "110.010";
	}

	else if (strcmp(recname, "goat") == 0) {
		return "111.001";
	}

	else if (strcmp(recname, "hawk") == 0) {
		return "111.010";
	}

	else return "000.000";
}