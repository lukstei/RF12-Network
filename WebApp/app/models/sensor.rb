class Sensor < ActiveRecord::Base
	belongs_to :station
	has_many :measured_datas
end
