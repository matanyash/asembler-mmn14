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

/*A function that encodes the first line*/
void binaryFirstLine(char *word1, char *word2, int act, StringTableBIN *table);

/*A function that converts using the base 64 method*/
void base64_encode(const char* input, char* output);

/*A function that creates the final file*/
void process_input_file(StringTableBIN *table, const char* output_filename);

/*A function that creates the entry file*/
void process_input_file_ent(const char* output_filename);

/*A function that creates the external file*/
void process_input_file_ext(const char* output_filename, StringTableBIN *table);

/*Binary coding of the operations*/
void binaryActioen(char *line , StringTableBIN *table);

int chekLineEror(char * line_copy);

/*initialization of the table*/
void initParamTable();

/*Updating the symbol table with the numerical value, symbol name and symbol type*/
int addParamToTable(int ID, const char *Label, const char *Type);

void duplicateDataWithType(int number);

int checkIfWordExists(ParamTable *table,char *word);

/*The function goes line by line on the input and encodes the first line and inserts the symbols into the table*/
void processFile(const char *filename);

/*The function goes line by line on the input and encodes a second line and ends the encoding*/
void SecondPass(const char *filename, StringTableBIN *tableBin1);

int main();


#endif
