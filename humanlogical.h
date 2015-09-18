// Replace physical numbers with human names
char* humanToLogicalLookup(char* recname)
{
	if (strcmp(recname, "user1") == 0) {
		return "100.001";
	}

	else if (strcmp(recname, "user2") == 0) {
		return "100.010";
	}

	else if (strcmp(recname, "user3") == 0) {
		return "101.001";
	}

	else if (strcmp(recname, "user4") == 0) {
		return "101.010";
	}

	else if (strcmp(recname, "user5") == 0) {
		return "110.001";
	}

	else if (strcmp(recname, "user6") == 0) {
		return "110.010";
	}

	else if (strcmp(recname, "user7") == 0) {
		return "111.001";
	}

	else if (strcmp(recname, "user8") == 0) {
		return "111.010";
	}

	else return "000.000";
}