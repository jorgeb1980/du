========================================================================
    APLICACIÓN: du Información general del proyecto
========================================================================

AppWizard ha creado esta aplicación du.  

Este archivo incluye un resumen acerca del contenido de los archivos que 
constituyen su aplicación du.

du.vcxproj
    Éste es el archivo de proyecto principal para los proyectos de VC++ 
    generados mediante un Asistente para aplicaciones. 
    Contiene información acerca de la versión de Visual C++ con la que se 
    generó el archivo, así como información acerca de las plataformas, 
    configuraciones y características del proyecto seleccionadas en el 
    asistente para aplicaciones.

du.vcxproj.filters
    Éste es el archivo de filtros para los proyectos de VC++ generados mediante 
    un asistente para aplicaciones. 
    Contiene información acerca de la asociación entre los archivos de un 
    proyecto y los filtros. Esta asociación se usa en el IDE para mostrar la 
    agrupación de archivos con extensiones similares bajo un nodo específico 
    (por ejemplo, los archivos ".cpp" se asocian con el filtro
    "Archivos de código fuente").

du.cpp
    Ésta es la aplicación principal del archivo de código fuente.

AssemblyInfo.cpp
    Contiene atributos personalizados para modificar metadatos de 
    ensamblado.

/////////////////////////////////////////////////////////////////////////////
Otras notas:

El asistente para aplicaciones utiliza "TODO:" para indicar las partes del 
código fuente que tendría que agregar o personalizar.

/////////////////////////////////////////////////////////////////////////////


Ayuda de la herramienta du

Usage: du [OPTION]... [FILE]...
Summarize disk usage of each FILE, recursively for directories.

  -a, --all             write counts for all files, not just directories
  -b, --bytes           print size in bytes
  -c, --total           produce a grand total
  -D, --dereference-args  dereference PATHs when symbolic link
  -h, --human-readable  print sizes in human readable format (e.g., 1K 234M 2G)
  -k, --kilobytes       use 1024-byte blocks, not 512 despite POSIXLY_CORRECT
  -l, --count-links     count sizes many times if hard linked
  -L, --dereference     dereference all symbolic links
  -m, --megabytes       use 1024K-byte blocks, not 512 despite POSIXLY_CORRECT
  -S, --separate-dirs   do not include size of subdirectories
  -s, --summarize       display only a total for each argument
  -x, --one-file-system  skip directories on different filesystems
      --help            display this help and exit
      --version         output version information and exit