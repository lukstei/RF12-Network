class Sensor < ActiveRecord::Base
	
	belongs_to :task
	belongs_to :sensor_type
	belongs_to :station
	has_many :measured_datas
	
	 validates :name, :station, :presence => true
	 validates :sensor_type, :presence => true 
	 
end
