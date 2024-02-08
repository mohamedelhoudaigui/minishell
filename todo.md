check makefile paths for readline :)

operator expantion QUOTES
heredoc delimiter should not expande !

export gg=$USER should expande !
export $USER=gwgr should expande !

echo $USE should not expande -> its in strncmp

check redirections expantion : delimiter should not expande !


ls > "'$USER'" should not be an ls flag !!!