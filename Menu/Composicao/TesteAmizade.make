##################################################
###
### Diretivas de MAKE para o construto: TesteAmizade
### Gerado a partir de: ..\Composicao\TesteAmizade.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteAmizade


### Nomes de paths

Ph                   = ..\Fontes
Pobj                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Fontes
Pc                   = ..\Fontes

### Nomes de diretórios para geração

Fh                   = ..\Fontes
Fobj                 = ..\Objetos
Ferr                 = ..\Produto
FDEFAULT             = ..\Fontes
Fc                   = ..\Fontes

### Macros da plataforma


O       = /D_CRT_SECURE_NO_DEPRECATE
OD      = /Zi /Od /D_CRT_SECURE_NO_DEPRECATE
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de geração

all : limpa \
   $(Fobj)\testeamizade.obj   $(Fobj)\amizade.obj   $(Fobj)\grafo.obj \
   $(Fobj)\perfil.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\testeamizade.obj :  {$(Pc)}\testeamizade.c \
    {$(Ph)}amizade.h            {$(Ph)}cespdin.h            {$(Ph)}generico.h           \
    {$(Ph)}grafo.h              {$(Ph)}lerparm.h            {$(Ph)}lista.h              \
    {$(Ph)}perfil.h             {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\amizade.obj :  {$(Pc)}\amizade.c \
    {$(Ph)}amizade.h            {$(Ph)}cespdin.h            {$(Ph)}grafo.h              \
    {$(Ph)}lista.h              {$(Ph)}perfil.h            
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\grafo.obj :  {$(Pc)}\grafo.c \
    {$(Ph)}cespdin.h            {$(Ph)}grafo.h              {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\perfil.obj :  {$(Pc)}\perfil.c \
    {$(Ph)}grafo.h              {$(Ph)}lista.h              {$(Ph)}perfil.h            
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\testeamizade.obj   $(Fobj)\amizade.obj   $(Fobj)\grafo.obj \
   $(Fobj)\perfil.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TesteAmizade
###
##################################################

