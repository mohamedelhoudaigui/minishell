check exit status of builtins or other exit status , done need testing
pipe problems with redirection, done need testing for multi redirections in multi commands
implement expander, done need to complete heredoc
heredoc compilted.
now we need to tackle file descriptors openning and morph the given struct to produce the execution struct, done


heredoc file is unseted so it cant be deleted even after sleeping (seems like, test it more), fixed

commands still execute when fd is -1 ! , done fixed

need expantion in parsing !


/// merge todo :

cat | cat | cat | ls

redirection with no command is a valid command !!


use after free check sanitizer

linked list head is lost after unseting the first variable

export accepts quotes !!

command with no args doesnt execute