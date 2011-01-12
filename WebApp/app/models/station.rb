class Station < ActiveRecord::Base
	has_many :sensors
	
	validates :adress, :uniqueness => true
	
end
