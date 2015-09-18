char* humanToLogicalLookup(char* recname)
{
	if (strcmp(recname, "41") == 0) {
		return "100.001";
	}

	else if (strcmp(recname, "42") == 0) {
		return "100.010";
	}

	else if (strcmp(recname, "51") == 0) {
		return "101.001";
	}

	else if (strcmp(recname, "52") == 0) {
		return "101.010";
	}

	else if (strcmp(recname, "61") == 0) {
		return "110.001";
	}

	else if (strcmp(recname, "62") == 0) {
		return "110.010";
	}

	else if (strcmp(recname, "71") == 0) {
		return "111.001";
	}

	else if (strcmp(recname, "72") == 0) {
		return "111.010";
	}

	else return "000.000";
}