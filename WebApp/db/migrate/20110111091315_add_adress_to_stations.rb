class AddAdressToStations < ActiveRecord::Migration
  def self.up
	add_column :stations, :adress, :string
  end

  def self.down
	remove_column :stations, :adress
  end
end
