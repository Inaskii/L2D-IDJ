make clean # apaga os arquivos gerados pelo build
make debug # compila com simbolos de debug (-ggdb -O0)
gdb ./JOGO # abre o programa dentro do debugger
# run inicia a execucao do programa
# bt mostra a pilha de chamadas quando der erro
# frame 0  vai para o frame onde o erro aconteceu
# list  mostra o codigo fonte ao redor da linha atual
# info locals  mostra as variaveis locais do frame atual
# break NomeDaFuncao # para a execucao em uma funcao especifica
# continue  continua a execucao depois de um break
# next  executa a proxima linha sem entrar em funcoes
# step  executa a proxima linha entrando em funcoes
# print variavel  mostra o valor de uma variavel
