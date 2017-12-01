@ECHO  OFF
REM Compila todos os .makes
REM Requer o ambiente (environment) inicializado para compilar com o VisualStudio

cls

del ..\Produto\*.err
del ..\Objetos\*.obj
del ..\Produto\*.exe

REM compila para producao sem otimizacoes
pushd .
nmake /F..\composicao\TesteMensagem.make 
popd


copy ..\Produto\*.err ..\Produto\tudo.err

notepad ..\Produto\tudo.err

