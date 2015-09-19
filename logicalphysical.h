char* logicalToPhysicalLookup(char* recname, char* routname)
{
	// 47
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

	// 57
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

	// 67
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

	// 44
	else if (strcmp(routname, "100.100") == 0) {
		if (strcmp(recname, "110.001") == 0) {
			return "61";
		}
		else if (strcmp(recname, "100.001") == 0) {
			return "41";
		}
		else return "47";
	}

	// 45
	else if (strcmp(routname, "100.101") == 0) {
		if (strcmp(recname, "110.010") == 0) {
			return "62";
		}
		else if (strcmp(recname, "100.010") == 0) {
			return "42";
		}
		else return "57";
	}

	// 46
	else if (strcmp(routname, "100.110") == 0) {
		if (strcmp(recname, "100.001") == 0) {
			return "41";
		}
		else if (strcmp(recname, "101.001") == 0) {
			return "51";
		}
		else return "67";
	}

	// 54
	else if (strcmp(routname, "101.100") == 0) {
		if (strcmp(recname, "100.010") == 0) {
			return "42";
		}
		else if (strcmp(recname, "101.010") == 0) {
			return "52";
		}
		else return "47";
	}

	// 55
	else if (strcmp(routname, "101.101") == 0) {
		if (strcmp(recname, "101.001") == 0) {
			return "51";
		}
		else if (strcmp(recname, "110.001") == 0) {
			return "61";
		}
		else return "57";
	}

	// 56
	else if (strcmp(routname, "101.110") == 0) {
		if (strcmp(recname, "101.010") == 0) {
			return "52";
		}
		else if (strcmp(recname, "110.010") == 0) {
			return "62";
		}
		else return "67";
	}

	// 64
	else if (strcmp(routname, "110.100") == 0) {
		if (strcmp(recname, "110.010") == 0) {
			return "62";
		}
		else if (strcmp(recname, "100.001") == 0) {
			return "41";
		}
		else return "47";
	}

	// 65
	else if (strcmp(routname, "110.101") == 0) {
		if (strcmp(recname, "110.001") == 0) {
			return "61";
		}
		else if (strcmp(recname, "100.010") == 0) {
			return "42";
		}
		else return "57";
	}

	// 66
	else if (strcmp(routname, "110.110") == 0) {
		if (strcmp(recname, "100.010") == 0) {
			return "42";
		}
		else if (strcmp(recname, "101.001") == 0) {
			return "51";
		}
		else return "67";
	}

	// 74
	else if (strcmp(routname, "111.100") == 0) {
		if (strcmp(recname, "100.001") == 0) {
			return "41";
		}
		else if (strcmp(recname, "101.010") == 0) {
			return "52";
		}
		else return "47";
	}

	// 75
	else if (strcmp(routname, "100.101") == 0) {
		if (strcmp(recname, "101.010") == 0) {
			return "52";
		}
		else if (strcmp(recname, "110.001") == 0) {
			return "61";
		}
		else return "57";
	}

	// 76
	else if (strcmp(routname, "111.110") == 0) {
		if (strcmp(recname, "101.001") == 0) {
			return "51";
		}
		else if (strcmp(recname, "110.010") == 0) {
			return "62";
		}
		else return "67";
	}

	else return "00";
}

/*
char* logicalToPhysicalConvert(char* logname)
{
	char address[7];
	char first[3];
	char last[3];
	char* p_address;
	int i_first;
	int i_last;
	int i_p_address;

	strcpy(address, logname);
	for (int i = 0; i < 3; i++)
	{
		first[i] = address[i];
		last[i] = address[i + 4];
	}

	i_first = strtol(first, NULL, 2);
	i_last = strtol(last, NULL, 2);
	i_p_address = (i_first * 10) + i_last;
	sprintf(p_address, "%d", i_p_address);

	return p_address;
}*/