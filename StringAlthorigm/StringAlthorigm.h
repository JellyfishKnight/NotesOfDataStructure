//
// Created by wjy on 22-7-2.
//

#ifndef DATASTRUCTURE_STRINGALTHORIGM_H
#define DATASTRUCTURE_STRINGALTHORIGM_H


int baseMatch(char *p, char *t);

int *buildNext(char *p);

int kmpMatch(char *p, char *t);

int bmMatch(char *p, char *t);

int *buildBC(char *p);

int *buildSS(char *p);

int *buildGS(char *p);

#endif //DATASTRUCTURE_STRINGALTHORIGM_H