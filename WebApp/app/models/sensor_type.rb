class SensorType < ActiveRecord::Base
	has_many :sensors
	
	validates :name, :unit, :interface, :presence => true
	
end
