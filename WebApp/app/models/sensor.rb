class Sensor < ActiveRecord::Base
	belongs_to :station
	belongs_to :task
	belongs_to :sensor_type
	has_and_belongs_to_many :groups 
	has_many :measured_datas
end
