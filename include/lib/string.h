size_t strlen(char **string)
{
	if(*string) {
		size_t i;
		while((*string)[i] != '\0') i++;
		return i;
	} else return 0;
}
