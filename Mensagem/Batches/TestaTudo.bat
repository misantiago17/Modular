REM Executa os testes de todos os scripts atrav�s dos constructos .exe

cls

if exist ..\Scripts\estatisticas.estat  del ..\Scripts\estatisticas.estat

..\Produto\TRAB4-10	/s..\Scripts\TesteMensagem	/l..\Produto\TRAB4-10	/a..\Scripts\estatisticas


..\..\Tools\exbestat /e..\Scripts\estatisticas
