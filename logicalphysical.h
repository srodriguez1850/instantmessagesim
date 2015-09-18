char* logicalToPhysicalLookup(char* recname, char* routname)
{
	if (strcmp(routname, "100.111") == 0) {
		if (strcmp(recname, "100.001") == 0) {
			return "41";
		}
		else if (strcmp(recname, "100.010") == 0) {
			return "42";
		}
		else if (strcmp(recname, "101.001") == 0) {
			return "51";
		}
		else if (strcmp(recname, "110.001") == 0) {
			return "61";
		}
		else return "57";
	}

	else if (strcmp(routname, "101.111") == 0) {
		if (strcmp(recname, "101.001") == 0) {
			return "51";
		}
		else if (strcmp(recname, "101.010") == 0) {
			return "52";
		}
		else if (strcmp(recname, "110.010") == 0) {
			return "62";
		}
		else if (strcmp(recname, "100.010") == 0) {
			return "42";
		}
		else return "67";
	}

	else if (strcmp(routname, "110.111") == 0) {
		if (strcmp(recname, "110.001") == 0) {
			return "61";
		}
		else if (strcmp(recname, "110.010") == 0) {
			return "62";
		}
		else if (strcmp(recname, "101.010") == 0) {
			return "52";
		}
		else if (strcmp(recname, "100.001") == 0) {
			return "41";
		}
		else return "47";
	}

	else return "00";
}