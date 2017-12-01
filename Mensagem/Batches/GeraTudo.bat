@ECHO  OFF
REM Gera os arquivos .make, .build e .list pelos arquivos .comp

pushd  .

cd ..\..\Tools
gmake /b..\Mensagem\Composicao /c..\Composicao\TesteMensagem


popd
