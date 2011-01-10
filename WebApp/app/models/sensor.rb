class Sensor < ActiveRecord::Base
	belongs_to :station
	belongs_to :task
	belongs_to :sensor_type
	has_many :measured_datas
	
	 validates :name, :port, :station, :presence => true
	 validates :sensor_type, :presence => true 
	
	
end
