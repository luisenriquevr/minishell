# minishell

while ; true ; do leaks minishell ; sleep 1 ; done

Cosas que faltan:

"<< h" da segfault

ctrl+\ dentro de cat o cualquier proceso a la espera

ctrl+C dentro de heredoc tiene que salir sin ejecutar

Mirar el caso de "unclosed quotes" y decidir qué hacer: ahora lanza el mensaje pero aún así ejecuta. Yo lo pararía, pero lo que he intentado hacer no funciona (funcion clear_line del main.c)

Cómo no, la expansión: arreglar el trim_quotes

