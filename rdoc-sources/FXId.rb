module Fox
  #
  # Encapsulates a server side resource.
  #
  class FXId < FXObject

    # Application {FXApp}
    attr_reader :app

    # User data [Object]
    attr_accessor :userData

    # XID handle for the server-side resource [Integer]
    attr_reader :xid

    #
    # Create resource.
    #
    def create(); end

    # Returns true if this resource has been created.
    def created?; end

    #
    # Detach resource.
    #
    def detach(); end

    #
    # Destroy resource.
    #
    def destroy(); end

    # Runs the specified block on the UI thread.
    #
    # The block is posted to the event queue of the UI thread.
    def runOnUiThread(&block); end
  end
end
