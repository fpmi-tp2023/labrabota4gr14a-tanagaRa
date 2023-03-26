	// Insert into table

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main(int argc, char* argv[]) {
	sqlite3 *db;
	char *ErrMsg = 0;
	int rc;
	char *sql;

	// Opening DB
	rc = sqlite3_open("test.db", &db);

	if (rc) {
		fprintf("Error while opening db: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;	
	} else {
		fprintf(stdout,"Database opened successfully\n");
	}

	// Creating SQL statement
	sql = "INSERT INTO Cars (Id, Name, Price) VALUES " \
	       "(1, 'Audi', 20323.43)," \
	       "(2, 'Scoda', 43902.22)," \
	       "(3, 'Opel', 22962.79);"; 
	
	//Executong SQL statement
	rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", ErrMsg);
		sqlite3_free(ErrMsg);
		sqlite3_close(db);
		return 1;
	} else {
		fprintf(stdout,"Data inserted successfully.\n");
	}

	sqlite3_close(db);
	return 0;
}
