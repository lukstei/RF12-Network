class Station < ActiveRecord::Base
	has_many :sensors
end
