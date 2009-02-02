#!/usr/local/bin/ruby

def build_project(topdir, project)
  dspfile = [topdir, 'windows', 'vcpp', project, project + '.dsp'].join(File::ALT_SEPARATOR)

  # Modify the project file to compile-in support for non-native
  # image file formats
  bytes = nil
  File.open(dspfile, 'rb') { |f| bytes = f.read }
  bytes.sub!('/D "HAVE_GL_H" /D "HAVE_GLU_H"',
             '/D "HAVE_GL_H" /D "HAVE_GLU_H" /D "HAVE_JPEG_H" /D "HAVE_PNG_H" /D "HAVE_TIFF_H"')
  bytes.sub!('glu32.lib',
             'glu32.lib libpng.lib zlib.lib libjpeg.lib libtiff.lib')
  File.open(dspfile, 'wb') { |f| f.write(bytes) }

  # Build the library
  system("msdev #{dspfile} /make \"#{project} - Win32 Release\"")
end

if __FILE__ == $0
  if ARGV.length != 1
    puts 'Usage: build-fox [fox-src-dir]'
    exit
  end

  topdir = ARGV[0]
  puts "Building library in #{topdir}..."

  build_project(topdir, 'fox')
# build_project(topdir, 'foxdll')
end
