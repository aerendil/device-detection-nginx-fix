﻿#include <stdio.h>
#include <string.h>
#include "51Degrees.h"

#ifdef _MSC_VER
#define _INTPTR 0
#endif

#define BUFFER_LENGTH 50000

int main(int argc, char* argv[]) {
	Workset *ws = NULL;
	DataSet dataSet;
	char output[BUFFER_LENGTH];
	char *fileName = argc > 1 ? argv[1] : NULL;
    char *requiredProperties = argc > 2 ? argv[2] : NULL;

    if (fileName != NULL &&
        initWithPropertyString(fileName, &dataSet, requiredProperties) > 0) {

		ws = createWorkset(&dataSet);

        #ifdef _MSC_VER
        gets_s(ws->input, dataSet.header.maxUserAgentLength);
        #else
        gets(ws->input);
        #endif
		while(strlen(ws->input) > 0) {
			match(ws, ws->input);
			if (ws->profileCount > 0) {
				processDeviceCSV(ws, output, BUFFER_LENGTH);
				printf("%s", output);
			}
			else {
				printf("null\n");
			}

			// Flush buffers.
			fflush(stdin);
			fflush(stdout);

			// Get the next useragent.
            #ifdef _MSC_VER
            gets_s(ws->input, dataSet.header.maxUserAgentLength);
            #else
            gets(ws->input);
            #endif
		}

		freeWorkset(ws);
		destroy(&dataSet);
	}

	return 0;
}
