class SensorType < ActiveRecord::Base
	has_many :sensors

	validates :name, :unit, :presence => true
	
end
