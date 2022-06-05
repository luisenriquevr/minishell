# minishell

while ; true ; do leaks minishell ; sleep 1 ; done

Cosas que faltan:

arreglar SHLVL -> solucionado

Mirar el caso de "unclosed quotes" y decidir qué hacer: ahora lanza el mensaje pero aún así ejecuta. Yo lo pararía, pero lo que he intentado hacer no funciona (funcion clear_line del main.c) -> solucionado

Cómo no, la expansión: arreglar el trim_quotes -> solucionado

"<< h" da segfault -> solucionado

env -i ./minishell error -> solucionado

arreglar la impresion de export -> solucionado

ctrl+C dentro de heredoc tiene que salir sin ejecutar -> solucionado

ctrl+d dentro de heredoc, tiene que ser como si pusieras EOF -> solucionado

ctrl+\ dentro de cat o cualquier proceso a la espera -> solucionado

generacion de heredocs en distintos archivos -> solucionado

salida de heredoc correctamente -> solucionado