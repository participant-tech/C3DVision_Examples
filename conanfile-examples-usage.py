# conanfile-examples-usage.py is a ready to use prototype to build Examples source code packaged by 'c3dvision-examples' package with conan.

# For manual build user should:
#
# 1. Have installed conan 2 package manager.
# 2. Set up desired c3d kernel and c3dvision packages versions in this recipe (see requirements() method).
# 3. Get hashtag of any of the installed c3dvision-examples packages in local conan repository
#    conan cache path c3dvision-examples/1.2.3.4
#    where c3dvision version is 1.2.3.4 (use actual).
# 4. Get installed c3dvision-examples package folder path with:
#    conan cache path c3dvision-examples/1.2.3.4:8bd97e051657dbddf12ce25d94d9d7fe4c8ccfa1
# where 8bd97e051657dbddf12ce25d94d9d7fe4c8ccfa1 is the found hashtag.
# 5. Copy conanfile-examples-usage.py file from the c3dvision-examples package folder e.g.
#    /home/user_name/.conan2/p/b/c3dvi<some-hash-from-step-4>/p/src/Examples
#    to any other folder,
# 6. Build with this recipe the Examples source code located in c3dvision-examples package folder


# Under Linux (it was checked for Ubuntu 24.04.01 LTS) it may be necessary to install conan and to work with conan out of activated virtual environment.
# To create virtual environment for python3 (it was checked under Python 3.12.3) user may run once the following commands:
#
# $> mkdir -p ~/.venv/vuser_conan
# $> python3 -m venv ~/.venv/vuser_conan
# $> ~/.venv/vuser_conan/bin/python -m pip install conan
#
# To activate the  virtual environment run
#
# $> . ~/.venv/vuser_conan/bin/activate
# or
# $> source ~/.venv/vuser_conan/bin/activate
#
# To upgrade conan run
# $> pip install conan --upgrade.


## Build Examples source code e.g. with the following commands called from folder with copied recipe (for Debug configuration):
#
# $> conan build conanfile-examples-usage.py --build=missing --options:h="&:with_unicode=True" --options="c3d/*:shared=True" -pr:h default -of build-debug -s:h build_type=Debug
#
# Executables and config files will be created in 'build-debug/bin/' subfolder.
# To run under Linux call 'sh run.sh app_name' command in terminal from the folder where it is located, under Windows just run from explorer.
#


import os
import shutil
from conan import ConanFile, tools
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.files import copy, save
from conan import conan_version
if conan_version >= '2.12.0':
  from conan.internal.model.conanfile_interface import ConanFileInterface
else:
  from conans.model.conanfile_interface import ConanFileInterface

required_conan_version = '>=2.0.5'

# Examples source dirs exported to the c3dvision-examples package 'src' folder
C3DVISION_EXAMPLES_SOURCE_DIR = 'Examples'

class C3DVisionConanExamplesUsage(ConanFile):
  name = 'c3dvision-examples-usage'
  license = 'Commercial'
  author = 'C3D Labs LLC'
  homepage = 'https://c3dlabs.com'
  url = 'https://c3dlabs.com'
  description = 'Recipe to build c3dvision-examples package Examples source code.'
  settings = 'os', 'compiler', 'build_type', 'arch'

  options = {  # Are passed transparately to the requested c3d/c3dvision package options
    'with_unicode': [True, False],
    'cmake_options': ['ANY']
  }
  default_options = {
    'with_unicode': True,
    'cmake_options': [None]
  }

  package_type = 'application'

  version = '1.0.0'

  def requirements(self):
    print('>> Processing requirements...')
    self.requires('c3d/2025.1.11803.8',
      options = {
        'shared': True,
        'with_unicode': self.options.with_unicode.value
      },
      package_id_mode='patch_mode'
    )
    c3dvision_version = '2.14.0-dev.64'
    self.requires(f'c3dvision/{c3dvision_version}',
      options = {
        'shared': True,
        'with_unicode': self.options.with_unicode.value
      },
      package_id_mode='patch_mode'
    )
    self.requires(f'c3dvision-examples/{c3dvision_version}',
      options= {
        'shared': True,
        'with_unicode': self.options.with_unicode.value
      },
      package_id_mode='patch_mode'
    )

    self.requires('qt/5.15.16', options={'shared': True})
    self.requires('freetype/2.13.3', override=True)  # Since qt/5.15.16 expects older freetype/2.13.2 and we want to minimize compiled binaries quantity
    self.requires('openssl/1.1.1w', override=True)  # Use the same version as expected by the c3dvision package
    self.requires('opengl/system')

  @property
  def _min_cppstd(self):
    return 17


  def _configure_cmake(self, cmake):
    if self.settings.compiler == 'msvc':
      if self.settings.compiler.version == 192:
        cmake.generator = 'Visual Studio 16 2019'
      elif (self.settings.compiler.version == 193 or self.settings.compiler.version == 194):
        cmake.generator = 'Visual Studio 17 2022'
      else:
        self.output.error(f'CMake generator for MSVC compiler version {self.settings.compiler.version} is not supported.')
    else:
      cmake.generator = 'Unix Makefiles'


  def _deploy_c3d_libs(self):
    # Deploy dependent shared libs to the build folder
    host_c3d_pkg = f"c3d/{self.dependencies['c3d'].ref.version}"
    c3d: ConanFileInterface = self.dependencies.host[host_c3d_pkg]
    host_c3dvision_pkg = f"c3dvision/{self.dependencies['c3dvision'].ref.version}"
    c3dvision: ConanFileInterface = self.dependencies.host[host_c3dvision_pkg]

    pkgs_dst_dir: str = os.path.join(self.build_folder, 'bin')
    if self.settings.os == 'Windows':
      pkgs_dst_dir = os.path.join(pkgs_dst_dir, self.settings.build_type.value)

    self.output.info(f"Deploying \'{host_c3d_pkg}\' package shared library from the {c3d.package_folder}")
    self.output.info(f"Deploying \'{host_c3dvision_pkg}\' package shared library from the {c3dvision.package_folder}")
    for lib in [ c3d.package_folder, c3dvision.package_folder ]:
      if self.settings.os == 'Windows':
        for item in [ '*.dll' ]:
          copy(self, item, src=os.path.normpath(f'{lib}/bin'), dst=pkgs_dst_dir, keep_path=False)
      else:
        for item in [ '*.so.*', '*.so', '*.so.*.*', '*.dylib' ]:
          copy(self, item, src=os.path.normpath(f'{lib}/lib'), dst=pkgs_dst_dir, keep_path=False)


  def _deploy_qt_libs(self):
    pkgs_dst_dir: str = os.path.join(self.build_folder, 'bin')
    if self.settings.os == 'Windows':
      pkgs_dst_dir = os.path.join(pkgs_dst_dir, self.settings.build_type.value)

    # Create qt.conf to point to the Qt package plugins folder
    host_qtx_pkg = f"qt/{self.dependencies['qt'].ref.version}"
    qtx: ConanFileInterface = self.dependencies.host[host_qtx_pkg]

    deploy_qt_lib: bool = True  # self.conf.get('user.qt_lib:deploy')
    QT_CONF_FILE = 'qt.conf'
    conf_line: str = 'Prefix=.'
    save(self, os.path.join(pkgs_dst_dir, QT_CONF_FILE), '[Paths]\n')
    if not deploy_qt_lib:
      if self.settings.os == 'Windows':
        conf_line = (f'Prefix={qtx.package_folder}').replace('\\', '/')  # Only forward slash '\' does for Windows
      else:
        conf_line = f'Prefix={qtx.package_folder}'  # Backslash does for Linux
    save(self, path=os.path.join(pkgs_dst_dir, QT_CONF_FILE), content=os.path.normpath(f'{conf_line}'), append=True)


    if self.settings.os == 'Windows':
      run_bat_file = os.path.join(pkgs_dst_dir, 'run.bat')
      save(self, run_bat_file, '@echo NOTE: Call \'run.bat app_name\' in the terminal to run the \'app_name\' executable,\n')
      save(self, run_bat_file, '@echo loading the dependent libraries from the paths in the modified PATH env variable.\n\n', append=True)
      save(self, run_bat_file, '@echo off\nchcp 65001\n', append=True)

      if deploy_qt_lib:
        conf_line = 'set PATH=.;%PATH%\n'
      else:
        conf_line = 'set PATH=' + os.path.join(qtx.package_folder, 'bin;') + f'{pkgs_dst_dir};' + '%PATH%\n'
        conf_line = conf_line.replace('\\', '/')

      save(self, run_bat_file, conf_line, append=True)
      save(self, run_bat_file, 'echo Running %* application...\n', append=True)
      save(self, run_bat_file, 'start %*\n', append=True)
    else:
      # Create run.sh script to setup LD_LIBRARY_PATH to run QT dependent apps
      run_sh_file = os.path.join(pkgs_dst_dir, 'run.sh')
      save(self, run_sh_file, '#!/bin/sh\n')
      save(self, run_sh_file,
        '# NOTE: Call \'sh run.sh ./<app_name>\' in the terminal from the folder where run.sh is created to run the ./<app_name> executable,\n', append=True)
      save(self, run_sh_file,
            '# loading the dependent libraries from the paths pointed by the LD_LIBRARY_PATH env variable.\n\n', append=True)
      if not deploy_qt_lib:
        conf_line = os.path.normpath(f'LD_LIBRARY_PATH={qtx.package_folder}/lib:{pkgs_dst_dir}\n')
      else:
        conf_line = 'LD_LIBRARY_PATH=.\n'
      save(self, run_sh_file, conf_line, append=True)
      save(self, run_sh_file, 'export LD_LIBRARY_PATH\n', append=True)
      save(self, run_sh_file, 'exec $@ &\n', append=True)


    # Deploy linked QtX libraries and plugins
    if deploy_qt_lib:
      self.output.info(f"Deploying '{host_qtx_pkg}' package shared libraries from the {qtx.package_folder}")
      shutil.copytree(src=os.path.join(qtx.package_folder, 'plugins'), dst=os.path.join(pkgs_dst_dir, 'plugins'), dirs_exist_ok=True)
      if self.settings.os == 'Windows':
        for item in [ '*.dll' ]:
          copy(self, item, src=os.path.join(qtx.package_folder, 'bin'), dst=pkgs_dst_dir, keep_path=False)
      else:
        for item in [ '*.so.*', '*.so', '*.so.*.*', '*.dylib' ]:
          copy(self, item, src=os.path.join(qtx.package_folder, 'lib'), dst=pkgs_dst_dir, keep_path=False)


  def build(self):
    print('>> build...')
    cmake = CMake(self)
    self._configure_cmake(cmake)
    print(f'Using {cmake.generator} cmake.generator.')

    host_c3dvision_examples_pkg = f"c3dvision-examples/{self.dependencies['c3dvision-examples'].ref.version}"
    c3dvision_examples: ConanFileInterface = self.dependencies.host[host_c3dvision_examples_pkg]
    self.output.info(f"Building Examples source code from \'{host_c3dvision_examples_pkg}\' package ({c3dvision_examples.package_folder})")

    cmake.configure(build_script_folder=os.path.normpath(f'{c3dvision_examples.package_folder}/src/{C3DVISION_EXAMPLES_SOURCE_DIR}'))
    # cmake.configure(build_script_folder='.')  # For debug
    cmake.build()

    print('Deploying dependent packages libraries:')
    self._deploy_c3d_libs()
    self._deploy_qt_libs()


  def generate(self):
    print('>> Generating project buildsystem...')
    deps = CMakeDeps(self)
    deps.generate()

    tc = CMakeToolchain(self)

    tc.cache_variables['CMAKE_BUILD_TYPE'] = self.settings.build_type.value
    # NOTE. The booleans assigned to variables/cache_variables will be translated to ON and OFF symbols in CMake
    tc.cache_variables['C3DVision_USING_UNICODE'] = (self.options.get_safe('with_unicode').value == 'True')
    tc.cache_variables['Examples_StandaloneBuildByConan:BOOL'] = True

    if tools.apple.is_apple_os(self):
      tc.cache_variables['CMAKE_FIND_ROOT_PATH_MODE_PROGRAM'] = 'BOTH'
      tc.cache_variables['CMAKE_FIND_ROOT_PATH_MODE_INCLUDE'] = 'BOTH'
      tc.cache_variables['CMAKE_FIND_ROOT_PATH_MODE_LIBRARY'] = 'BOTH'
      tc.cache_variables['CMAKE_FIND_ROOT_PATH_MODE_PACKAGE'] = 'NEVER'
      tc.cache_variables['CMAKE_MACOSX_BUNDLE'] = False
      tc.cache_variables['CMAKE_OSX_ARCHITECTURES'] = tools.apple.to_apple_arch(self)
    tc.generate()


  def layout(self):
    print('>> Creating layout...')
    # Create layout setting source and build subfolders
    cmake_layout(self, build_folder='.')
    self.folders.build = '.'
    self.folders.generators = 'generators'


  def package(self):
    print('>> Packaging project...')

    artifacts_dir = os.path.join(self.build_folder, 'bin')
    if self.settings.os == 'Windows':
      artifacts_dir = os.path.join(artifacts_dir, self.settings.build_type.value)

    print(f'artifacts_dir {artifacts_dir}')

    for item in [ '*.exe', 'qt.conf', 'run.*', '*.', '*.dll' ]:  # just copy something as an example
      copy(self, item, src=artifacts_dir, dst=os.path.join(self.package_folder, 'bin'), keep_path=False)


  def package_id(self):
    print('>> package_id...')
    del self.info.options.cmake_options
    print(f'Package id: {self.info.package_id()}')
