class Task < ActiveRecord::Base
	has_many :sensors
	
	validates :title, :description, :sensors, :presence => true 
end
