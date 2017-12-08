REM Executa os testes de todos os scripts através dos constructos .exe

cls

if exist ..\Scripts\estatisticas.estat  del ..\Scripts\estatisticas.estat


..\Produto\TRAB4-6  /s..\Scripts\TesteAmizade	/l..\Produto\TRAB4-6	/a..\Scripts\estatisticas



..\..\Tools\exbestat /e..\Scripts\estatisticas
