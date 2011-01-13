class Sensor < ActiveRecord::Base
	
	before_filter: 
	
	belongs_to :task
	belongs_to :sensor_type
	belongs_to :station
	has_many :measured_datas
	
	validates :name, :station, :presence => true
	validates :sensor_type, :presence => true 
	validates :analog_port, :presence => true, :if => :sensor_type_is_analog? 
		
	def sensor_type_is_analog?
		@sensor.sensor_type.is_analog
	end 
		
end
