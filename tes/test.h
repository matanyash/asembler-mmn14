#ifndef TEST
#define TEST

void initStringTable(StringTableBIN *table);

int addStringToStringTable(StringTableBIN *table, const char *str);

void updateTables(StringTableBIN *table1);

/*Symbol table update function*/
void upTabelLabel(char *label, int counter, char *type);

/*String binary encoding*/
void binaryString(const char *line, StringTableBIN *table);

/*Binary encoding function numbers*/
void binaryData(char *line, StringTableBIN *table);

void binaryFirstLine(char *word1, char *word2, int act, StringTableBIN *table);

void base64_encode(const char* input, char* output);

void process_input_file(StringTableBIN *table, const char* output_filename);

void process_input_file_ent(const char* output_filename);

void process_input_file_ext(const char* output_filename, StringTableBIN *table);

void binaryActioen(char *line , StringTableBIN *table);

int chekLineEror(char * line_copy);

/******************/

void initParamTable();

int addParamToTable(int ID, const char *Label, const char *Type);

void duplicateDataWithType(int number);

int checkIfWordExists(ParamTable *table,char *word);

/***************/
void processFile(const char *filename);

void SecondPass(const char *filename, StringTableBIN *tableBin1);

int main();


#endif
