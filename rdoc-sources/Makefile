SOURCES = *.rb \
        ../lib/fox/calendar.rb \
        ../lib/fox/chore.rb \
        ../lib/fox/core.rb \
        ../lib/fox/glgroup.rb \
        ../lib/fox/glshapes.rb \
        ../lib/fox/input.rb \
        ../lib/fox/iterators.rb \
        ../lib/fox/responder2.rb \
        ../lib/fox/scintilla.rb \
        ../lib/fox/signal.rb \
        ../lib/fox/timeout.rb \
        ../lib/fox/undolist.rb \
        ../lib/fox/version.rb

rdoc:
 @rdoc --op ../doc/api --main README.rdoc $(SOURCES) README.rdoc

ri:
 @rdoc --ri $(SOURCES)

clean:
 @rm -rf ../doc/api
