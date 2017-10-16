REM Executa os testes de todos os scripts através dos constructos .exe

cls

if exist ..\Scripts\estatisticas.estat  del ..\Scripts\estatisticas.estat

..\Produto\TRAB1-2  /s..\Scripts\TesteGrafo	/l..\Produto\TRAB1-2	/a..\Scripts\estatisticas


..\..\Tools\exbestat /e..\Scripts\estatisticas
