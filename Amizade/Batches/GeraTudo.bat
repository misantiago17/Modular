@ECHO  OFF
REM Gera os arquivos .make, .build e .list pelos arquivos .comp

pushd  .

cd ..\..\Tools
gmake /b..\Amizade\Composicao /c..\Composicao\TesteAmizade


popd
