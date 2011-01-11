class MeasuredData < ActiveRecord::Base
	belongs_to :sensor
	
	validates :messdaten_int, :presence => true
	validate :datatype_should_be_int
	
	def datatype_should_be_int
		errors.add(:sensor_id,":datatype must be integer") if :messdaten_int.class.to_s != "Fixnum"
	end 
	
end
