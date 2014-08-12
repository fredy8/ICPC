regmatch_t matches[1];
regcomp(&reg, pattern.c_str(),REG_EXTENDED|REG_ICASE);

if (regexec(&reg,str.c_str(),1,matches,0)==0)
    cout << "match" << endl;
regfree(&reg);