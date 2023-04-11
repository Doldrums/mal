#pragma once

void *init_enviroment();

char *parse_line(char *line);

char *eval_line(char *line, void *env);
