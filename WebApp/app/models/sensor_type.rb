class SensorType < ActiveRecord::Base
	has_many :sensors
	belongs_to :interface 
	
	validates :name, :unit, :presence => true
	
end
