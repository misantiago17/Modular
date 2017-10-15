REM Executa os testes de todos os scripts através dos constructos .exe

cls

if exist ..\Scripts\estatisticas.estat  del ..\Scripts\estatisticas.estat

..\Produto\TesteGrafo  /s..\Scripts\TesteGrafo	/l..\Produto\TesteGrafo	/a..\Scripts\estatisticas


..\..\Tools\exbestat /e..\Scripts\estatisticas
